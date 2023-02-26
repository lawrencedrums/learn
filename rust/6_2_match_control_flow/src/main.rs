#[derive(Debug)]
enum UsState {
    Alabama,
    Alaska,
}

enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter(UsState),
}

fn main() {
    let val = value_in_cents(Coin::Penny);
    assert!(val == 1);

    let five = Some(5);
    let six = plus_one(five);
    let none = plus_one(None);

    let dice_roll = 9;
    match dice_roll {
        3 => add_fancy_hat(),
        7 => remove_fancy_hat(),
        _ => (), // catch-all: all value except 3 or 7, nothing happens
    }
}

fn value_in_cents(coin: Coin) -> u8 {
    // compare a value against a series of patterns
    // execute code based on pattern matched
    // like `if` but can be evaluate to  any type
    match coin {
        // 4 arms, one for each variant in Coin
        Coin::Penny => {
            println!("Lucky penny!");
            1
        }
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter(state) => {
            println!("State quarter from {:?}!", state);
            25
        }
    }
}

fn plus_one(x: Option<i32>) -> Option<i32> {
    match x { 
        None => None,
        Some(i) => Some(i+1),
    }
}

fn add_fancy_hat() {}
fn remove_fancy_hat() {}
