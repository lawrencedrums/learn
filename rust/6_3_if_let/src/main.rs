enum Lang {
    Python,
    Rust,
}

fn main() {
    // if let is a less verbose way to handles values
    // that matches one pattern and ignore the rest
    let config_max = Some(3u8);
    if let Some(max) = config_max {
        println!("The maximum is configured to be {}", max);
    }
    // the above is the same as...
    // match config_max {
    //     Some(max) => println!("The maximum is configured to be {}", max),
    //     _ => (), // <- this line is annoying boilerplate!
    // }
    
    let mut count = 0;
    let lang = Lang::Rust;
    if let Lang::Rust = lang {
        count += 1;
        println!("{} Rust enjoyers", count);
    } else {
        println!("Python... typical");
    }
    // the above is the same as...
    // match lang {
    //     Lang::Rust => {
    //         println!("One of us! One of us!");
    //         count += 1;
    //     }
    //     _ => println!("Python... typical");
    // }
}
