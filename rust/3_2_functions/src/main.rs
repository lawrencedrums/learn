fn main() {
    // the box in {} is an expression; no semicolon
    // the whole `let x = ... };` line is a statement; yes semicolon
    let x = {
        let x = 3;
        x + 3
    };

    let num = add_five_print(x, 'H');
    println!("res: {num}");

    // if expects a bool type, so no i32
    if num % 4 == 0 {
        println!("divisible by 4");
    } else if num % 3 == 0 {
        println!("divisible by 3");
    } else {
        println!("what");
    }

    let pythonic = true;
    let excited = if pythonic {"One linerssss"} else {"boo"};
    println!("Rust is nice because {excited}\n");

    let mut counter = 0;
    let result = loop {
        counter += 1;

        if counter == 10 {
            break counter * 2;
        }
    };
    println!("result: {result}\n");

    // breaking out of different loops
    let mut count = 0;
    'counting_up : loop {
        println!("count: {count}");
        let mut remaining = 10;

        loop {
            println!("remaining: {remaining}");
            if remaining == 9 {
                break;
            }
            if count == 3 {
                break 'counting_up;
            }
            remaining -= 1;
        }

        count += 1;
    }
    println!("end count: {count}");

    count = 8;
    while count != 5 {
        println!("{count}");
        count -= 1 ;
    }

    let win = ["yay", "more", "pythonic", "syntax"];
    for element in win {
        println!("{element}");
    }

    for num in (1..4).rev() {
        println!("{num}");
    }
}

// expression:
// - evalute to a value
// - end without semicolon (;)
fn add_five_print(x: i32, letter: char) -> i32  {
    println!("letter: {letter}");

    x + 5
    // x + 5;
    //      ^
    //      expression doesn't return a value
}
