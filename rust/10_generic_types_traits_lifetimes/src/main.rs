struct Point<T> {
    x: T,
    y: T,
}

impl<T> Point<T> {
    fn x(&self) -> &T {
        &self.x
    }
}

impl Point<f32> {
    fn distance_from_origin(&self) -> f32 {
        (self.x.powi(2) + self.y.powi(2)).sqrt()
    }
}

fn main() {
    let num_list = vec![42, 666, 910, 2, 370];
    let str_list = vec!['y', 'm', 'c', 'a'];

    let largest_num = largest(&num_list);
    let largest_str = largest(&str_list);

    println!("Largest number: {largest_num}");
    println!("Largest string: {largest_str}");

    let integer_point = Point { x: 5, y: 2 };
    let float_point = Point { x: 4.0, y: 6.5 };
    // let wont_work = Point { x: 5, y: 6.5 };
    // to make the Point struct accept more than a type:
    // struct Point<T, U> {
    //     x: T,
    //     y: U,
    // }
    println!("p.x = {}", integer_point.x());
    println!("Distance from origin = {}", float_point.distance_from_origin());
}

// the function largest is generic over some type T,
// this function has one parameter named list, a slice of values of type T,
// this function will return a reference to a value of some type T
fn largest<T: std::cmp::PartialOrd>(list: &[T]) -> & T {
    let mut largest = &list[0];

    for i in list {
        if i > largest {
            largest = i;
        }
    }
    largest
}
