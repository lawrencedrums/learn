struct User {
    active: bool,
    username: String,
    email: String,
    sign_in_count: u64,
}

struct Color(i32, i32, i32);
struct Point(i32, i32, i32);

struct AlwaysEqual; // unit-like struct: struct with no fields

fn main() {
    let mut user1 = User {
        active: true,
        username: String::from("superuser1"),
        email: String::from("superuser@gmail.com"),
        sign_in_count: 1,
    };

    user1.email = String::from("superuser@django.admin");

    let u2_email = String::from("user@pm.me");
    let u2_username = String::from("normie");
    let user2 = build_user(u2_email, u2_username);

    let user3 = User {
        email: String::from("same_val@hotmail.com"),
        ..user2 // fill rest of struct with data from user2
    }; // this snip makes user2 invalid because the username field
       // was moved from user2 to user3
       // `active` and `sign_in_count` have the `Copy` trait, not affected
    
    let black = Color(0, 0, 0);
    let origin = Point(0, 0, 0);

    let subject = AlwaysEqual;
}

fn build_user(email: String, username: String) -> User {
    User {
        active: true,
        email,
        username,
        sign_in_count: 1,
    }
}
