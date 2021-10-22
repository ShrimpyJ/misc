package main

import (
	"fmt"
	"os"
	"strconv"
	"math/rand"
	"time"
)

const MS = 25

const (
	Up int = iota
	Right
	Down
	Left
)

type Guest struct {
	id          int
	pos         int
	moves       int
	facing      int
	m          *Maze
}

type Maze struct {
	pos       []byte
	length      int
}

type Shared struct {
	length        int
	completed     int
	guest_digits  int
	length_digits int
	concurrency   bool
	c             chan string
}

func (m *Maze) Init() {
	for i := 0; i < m.length*2-1; i++ {
		m.pos = append(m.pos, 'x')
	}
}

func (g *Guest) Print(length int) {
	for i := length-1; i >= 0; i-- {
		if g.pos == i*2 {
			fmt.Println("[O|")
		} else if g.pos == i*2+1 {
			fmt.Println("O |")
		} else {
			fmt.Println("[ |")
		}
	}
	fmt.Println()
	time.Sleep(MS * time.Millisecond)
}

func dirstr(dir int) string {
	var facing string
	if       dir == Up {
		facing = "UP"
	} else if dir == Right {
		facing = "RIGHT"
	} else if dir == Left {
		facing = "LEFT"
	} else if dir == Down {
		facing = "DOWN"
	}
	return facing
}

func (g *Guest) Move() int {
	var viable []int

	//fmt.Printf("Guest %d is facing %s on tile %d\n", g.id, dirstr(g.facing), g.pos)

	/* If in a dead end, turn around and walk out. Return new position */
	if g.pos % 2 != 0 {
		g.facing = Right
		g.pos--
		//fmt.Printf("Guest %d has entered and exited the dead end on tile %d and emerged facing Right on tile %d\n",
		//            g.id, g.pos+1, g.pos)
		return g.pos
	}

	/* If on the straightaway, find viable moves based on direction facing */
	if        g.facing == Up    {
		viable = append(viable, Up)
		viable = append(viable, Left)
	} else if g.facing == Right {
		viable = append(viable, Up)
		if g.pos != 0 {
			viable = append(viable, Down)
		}
	} else if g.facing == Down  {
		viable = append(viable, Left)
		if g.pos != 0 {
			viable = append(viable, Down)
		}
	}

	/* Roll random direction to attempt to move */
	/* Increment direction (if necessary) until viable direction is found */
	dir := rand.Intn(4)
	for true {
		for _, val := range viable {
			if dir == val {
				goto FOUND
			}
		}
		dir = (dir + 1) % 4
	}

FOUND:
	g.facing = dir

	if dir == Up {
		g.pos += 2
	} else if dir == Down {
		g.pos -= 2
	} else if dir == Left {
		g.pos += 1
	}

	if g.pos < 0 {
		g.pos = 0
	}

	return g.pos
}

func (g Guest) Print_Done(s *Shared) string {
	var str string
	str = fmt.Sprintf("Guest ")
	for i := 0; i < s.guest_digits - get_digits(g.id); i++ {
		str += fmt.Sprintf(" ")
	}
	str += fmt.Sprintf("%d has escaped after %12d moves\n", g.id, g.moves)
	return str
}

func (g Guest) Start(s *Shared) int {
	for g.pos < s.length*2 {
		//g.Print(s.length)
		g.Move()
		g.moves++
	}

	//g.Print(s.length)
	if s.concurrency {
		s.c <- g.Print_Done(s)
	} else {
		fmt.Printf("%s", g.Print_Done(s))
	}
	s.completed++

	return 0
}

func receive_channels(num_channels int, c chan string) {
	for i := 0; i < num_channels; i++ {
		fmt.Printf(<-c)
	}
}

func parse_args() (int, int, bool) {
	var concurrency bool
	var num_guests int

	length, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Fprintf(os.Stderr, "error: invalid length '%s' (must be an integer)\n", os.Args[1])
		os.Exit(3)
	}

	num_guests, err = strconv.Atoi(os.Args[2])
	if err != nil {
		fmt.Fprintf(os.Stderr, "error: invalid length '%s' (must be an integer)\n", os.Args[2])
		os.Exit(3)
	}

	if os.Args[3] == "y" {
		concurrency = true
	} else if os.Args[3] == "n" {
		concurrency = false
	} else {
		fmt.Fprintf(os.Stderr, "error: invalid concurrency option '%s' (must be y/n)\n", os.Args[3])
		os.Exit(3)
	}

	return length, num_guests, concurrency
}

func get_digits(n int) int {
	var i int

	if n == 0 {
		return 1
	}

	i = 0
	for n > 0 {
		n = n / 10
		i++
	}
	return i
}

func main() {
	rand.Seed(time.Now().UnixNano())

	var num_guests int
	var concurrency bool
	var guests []*Guest
	s := new(Shared)
	s.c = make(chan string)

	argc := len(os.Args[1:])
	if argc != 3 {
		fmt.Fprintf(os.Stderr, "usage: maze.go length guests concurrency(y/n)\n")
		os.Exit(3)
	}

	/* Get command line arguments */
	s.length, num_guests, concurrency = parse_args()
	fmt.Printf("Guests: %d\tLength: %d\n", num_guests, s.length)

	s.guest_digits  = get_digits(num_guests)
	s.length_digits = get_digits(s.length)
	s.concurrency   = concurrency

	/* Create Guests and start them on the maze */
	for i := 0; i < num_guests; i++ {
		g := new(Guest)
		g.id  = i
		g.pos = 0
		g.moves = 0
		g.facing = Up
		g.m = new(Maze)
		g.m.length = s.length
		g.m.Init()
		guests = append(guests, g)
		if concurrency {
			go g.Start(s)
		} else{
			g.Start(s)
		}
	}

	if concurrency {
		receive_channels(num_guests, s.c)
	}
}
