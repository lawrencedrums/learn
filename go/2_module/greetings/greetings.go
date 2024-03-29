package greetings

import (
    "errors"
    "fmt"
    "math/rand"
)

func Hello(name string) (string, error) {
    if name == "" {
        return "", errors.New("empty name")
    }

    // return a greeting that embeds the name in a message
    // message := fmt.Sprintf("Hello, %v. Welcome to Golang.", name)
    message := fmt.Sprintf(randomFormat(), name)
    // := declares and  initialize a variable
    return message, nil
}

func Hellos(names []string) (map[string]string, error) {
    messages := make(map[string]string)
    for _, name := range names {
        message, err := Hello(name)
        if err != nil {
            return nil, err
        }
        messages[name] = message
    }

    return messages, nil
}

func randomFormat() string {
    // a slice of message formats.
    formats := []string {
        "Hi, %v. Welcome to Golang!",
        "Great to see you, %v.",
        "Hail, %v! Well met!",
    }

    return formats[rand.Intn(len(formats))]
}
