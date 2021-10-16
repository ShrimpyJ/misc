package main

import (
	"fmt"
	"os"
	"strconv"
	"math/rand"
	"time"
)

type Process struct {
	id         int
	tickets    int
	iterations int
}

func find_ticket(ticket int, processes []Process) (int, *Process) {
	count := 0
	for i, p := range processes {
		count += p.tickets
		if count >= ticket {
			return i, &processes[i]
		}
	}
	return -1, nil
}

func main() {
	rand.Seed(time.Now().UnixNano())

	argc := len(os.Args[1:])
	fmt.Printf("Arg length is %d\n", argc)

	for i, a := range os.Args[1:] {
		fmt.Printf("Arg %d is %s\n", i+1, a)
	}

	if argc != 2 {
		fmt.Fprintf(os.Stderr, "usage: hello.go num_processes max_iterations\n")
		os.Exit(3)
	}

	num_processes, _    := strconv.Atoi(os.Args[1])
	max_iterations, err := strconv.Atoi(os.Args[2])

	max_tickets := 250
	digits      := 1
	num_tickets := 0
	temp        := num_processes

	if err != nil {
		fmt.Fprintf(os.Stderr, "error: invalid string conversion\n")
		os.Exit(3)
	}

	/* Get # of digits of processes for formatting purposes */
	for temp / 10 > 0 {
		temp = temp / 10
		digits++
	}

	var processes []Process
	for i := 0; i < num_processes; i++ {
		p := new(Process)
		p.id          = i
		p.tickets     = rand.Intn(max_tickets)
		p.iterations  = rand.Intn(max_iterations) + 1
		processes     = append(processes, *p)
		num_tickets  += p.tickets
	}

	for len(processes) >= 0 {
		if num_tickets == 0 {
			break
		}
		ticket := rand.Intn(num_tickets)
		i, p   := find_ticket(ticket, processes)

		//fmt.Printf("processes: %d\n", len(processes))
		//fmt.Println(*p)
		p.iterations--
		if p.iterations == 0 {
			num_tickets -= p.tickets
			processes[i] = processes[len(processes)-1]
			processes    = processes[:len(processes)-1]
		}
	}

	fmt.Println("All processes completed")
}
