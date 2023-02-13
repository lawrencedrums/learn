// const THREE_HOURS_IN_SECONDS: u32 = 60 * 60 * 3;

fn main() {
    // make x mutable
    let mut x = 5;
    println!("x: {x}");

    x = 6;
    println!("x: {x}\n");

    // Shadowing
    // - the second valuable overshadows the first
    let x = x + 1;
    {
        let x = x * 2;
        println!("x in inner scope: {x}");
    }
    println!("The value of x is: {x}");

    // mut: change only the value
    // let: change the type
    let spaces = "    ";
    let spaces = spaces.len();

    // give explicit type when parsing
    let guess: u32 = "42".parse().expect("Not a number!");
    
    // types
    let t = true;
    let f: bool = false; // explicit type annotation

    let c = 'z';
    let z: char = 'Z';

    // tuple
    let my_tup: (i32, f64, u8) = (500, 6.4, 1);
    let (x, y, z) = my_tup;
    println!("x: {x}\ny: {y}\nz: {z}");
    // or 
    // println!("x: {my_tup.0}\ny: {my_tup.1}\nz: {my_tup.2}");
    
    // arrays
    let arr = [3, 3, 3, 3, 3];
    let arr_type: [i32; 5] = [1, 2, 3, 4, 5]; // type of i32, 5 elements
    // or
    // let arr [3; 5]; // give five 3s
}
