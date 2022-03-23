package main

import (
	"fmt"
)

var stack = make([]string, 0)

type Rule struct {
	lhs string
	rhs []string
}

func print_stack() {
	fmt.Printf("-\n")
	for i := len(stack)-1; i >= 0; i-- {
		fmt.Printf("%s\n", stack[i])
	}
	fmt.Printf("-\n\n")
}

func push(item string) {
	stack = append(stack, item)
}

func pop() {
	stack = stack[:len(stack)-1]
}

func init_rules() []*Rule {
	var rules []*Rule

	rule := new(Rule)
	rule.lhs = "S"
	rule.rhs = append(rule.rhs, "aTb")
	rule.rhs = append(rule.rhs, "b")
	rules = append(rules, rule)

	rule = new(Rule)
	rule.lhs = "T"
	rule.rhs = append(rule.rhs, "Ta")
	rule.rhs = append(rule.rhs, "epsilon")
	rules = append(rules, rule)

	return rules
}

func print_rules(rules []*Rule) {
	for i := 0; i < len(rules); i++ {
		rule := rules[i]
		fmt.Printf("%s -> ", rule.lhs)
		for j := 0; j < len(rule.rhs); j++ {
			if (j == len(rule.rhs)-1) {
				fmt.Printf("%s", rule.rhs[j])
			} else {
				fmt.Printf("%s | ", rule.rhs[j])
			}
		}
		fmt.Printf("\n")
	}
}

func main() {
	// S -> aTb | b
	// T -> Ta | epsilon
	var rules = init_rules()

	print_rules(rules)

	str := "aaab"
	fmt.Printf("\nString: %s\n\n", str)

	// Start
	push("$")
	push("S")

	// Loop
	print_stack()
}
