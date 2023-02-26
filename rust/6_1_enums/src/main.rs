// `IpAddrKind` is now a custom type
enum IpAddrKind {
    V4,
    V6,
}

struct IpAddr {
    kind: IpAddrKind,
    address: String,
}

// more concisely represent the above concept with one enum
// each variant can have different types and amount of data
enum c_IpAddr {
    V4(u8, u8, u8, u8),
    V6(String),
}

enum Message {
    Quit, 
    Move { x: i32, y: i32 }, // named fields like a struct
    Write(String),
    ChangeColor(i32, i32, i32),
}

// you can implement methods for enums too!
impl Message {
    fn call(&self) {
        // method body
    }
}

fn main() {
    // create instances of the custom type's variant
    let four = IpAddrKind::V4;
    let six = IpAddrKind::V6;

    route(IpAddrKind::V4);

    let home = IpAddr {
        kind: IpAddrKind::V4,
        address: String::from("127.0.0.1"),
    };
    let loopback = IpAddr {
        kind: IpAddrKind::V4,
        address: String::from("::1"),
    };

    // attackdata to enum directly
    // IpAddr::V4() is a function call that takes a `String` aug
    // returns an instance of the `IpAddr` type
    let c_home = c_IpAddr::V4(127, 0, 0, 1);
    let c_loopback = c_IpAddr::V6(String::from("::1"));

    let m = Message::Write(String::from("hello"));
    m.call();

    let some_number = Some(5); // type is `Option<i32>`
    let some_char = Some('e'); 

    // have to annotate type
    let absent_number: Option<i32> = None;
}

fn route(ip_kind: IpAddrKind) {}
