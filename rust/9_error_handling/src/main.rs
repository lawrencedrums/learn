use std::error::Error;
use std::fs;
use std::fs::File;
use std::io::{self, ErrorKind, Read};

fn main() -> Result<(), Box<dyn Error>> {
    // Recoverable Errors with `Result`
    let file = File::open("hello.txt").unwrap_or_else(|error| {
        if error.kind() == ErrorKind::NotFound {
            File::create("hello.txt").unwrap_or_else(|error| {
                panic!("Problem creating the file: {:?}", error);
            })
        } else {
            panic!("Problem opening the file: {:?}", error);
        }
    });

    // `unwrap` is a shortcut for the match expression, it returns:
    //  if `Ok`, returns the value inside
    //  if `Err`, calls `panic!` for us
    let file_unwrap = File::open("hello.txt").unwrap();

    // `expect` let us choose the `panic!` error message
    let file_expect = File::open("world.txt").expect(".expect() returns this");

    let return_from_main_file = File::open("hello.txt")?;
    Ok(())
}

fn read_username_from_file() -> Result<String, io::Error> {
    let username_file_result = File::open("hello.txt");
    // let username_file_result = File::open("hello.txt")?;
    //
    // `?` is a shortcut that handles `Result` & `Option`, it returns:
    // if `Ok`, returns value inside `Ok`
    // if `Err`, returns early from the function with the `Err` msg

    let mut username_file = match username_file_result {
        Ok(file) => file,
        Err(e) => return Err(e),
    };

    let mut username = String::new();

    match username_file.read_to_string(&mut username) {
        Ok(_) => Ok(username),
        Err(e) => Err(e),
    }
    // username_file.read_to_string(&mut username)?;
    // Ok(username)
}

// this does the same thing as the above function
fn fs_read_username_from_file() -> Result<String, io::Error> {
    fs::read_to_string("hello.txt")
}
