#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

// functions in `impl` block are called associated functions
impl Rectangle {
    // self is an alias for the type that the `impl` block is for
    // pick `&self` because we don't want to take ownership
    fn area(&self) -> u32 {
        self.width * self.height
    }

    fn width(&self) -> bool {
        self.width > 0
    }

    fn can_hold(&self, other: &Rectangle) -> bool {
        self.width > other.width && self.height > other.height
    }

    // an associated function without `self` as first param
    // they don't need an instance of the type to work with
    fn square(size: u32) -> Self {
        Self {
            width: size,
            height: size,
        }
    }
}

fn main() {
    let rect1 = Rectangle {
        width: 30,
        height: 50,
    };
    let rect2 = Rectangle {
        width: 10,
        height: 40,
    };
    let rect3 = Rectangle {
        width: 60,
        height: 45,
    };

    println!(
        "The area of the rectangle is {} square pixels.",
        // the method syntax goes after an instance
        rect1.area()
    );

    if rect1.width() {
        println!("Width is nonzero: {}", rect1.width);
    }

    // main maintains ownership of `rect2` & `rect3`
    // because we are passing an immutable borrow
    println!("rect1 hold rect2? {}", rect1.can_hold(&rect2));
    println!("rect1 hold rect3? {}", rect1.can_hold(&rect3));

    // associated functions use the `::` syntax
    // also used for namespaces created by modules
    let sq = Rectangle::square(3);
    println!("Is it indeed a square?: {}", sq.width == sq.height);
}
