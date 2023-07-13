package main

import (
    "fmt"
    "log"

    "example.com/greetings"
)

func main() {
    // set properties of the predefined logger, including
    // the log entry prefix and a flag to disable printing
    // the time, source file, and line number
    log.SetPrefix("greetings: ")
    log.SetFlags(0)

    names := []string{"Blossom", "Bubbles", "Buttercup"}
    messages, err := greetings.Hellos(names)
    if err != nil {
        log.Fatal(err)
    }

    // get a greeting message and print it
    // message, err := greetings.Hello("Glados")
    // if err != nil { // there IS an error
    //     log.Fatal(err)
    // }

    fmt.Println(messages)
}
