#[derive(Debug)] // Implement `Debug` trait
struct Rectangle {
    width: u32,
    height: u32,
}

fn main() {
    let scale = 2;

    let rect1 = Rectangle {
        width: dbg!(30 * scale), // prints `stderr`; returns ownership
        height: 50,
    };

    println!(
        "The area of the rectangle is {}.",
        area(&rect1)
    );

    // error: rect1 doesn't have `Display` trait
    // println!("{}", rect1);
    println!("{:?}", rect1); // tell println to expect a `Debug` output
    dbg!(&rect1);
}

fn area(rectangle: &Rectangle) -> u32 {
    rectangle.width * rectangle.height
}
