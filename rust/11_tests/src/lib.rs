// cargo test --test-threads=1 // run tests without parallelism
// cargo test --show-output // show `println!` messages
// cargo test can_hold // run subset of tests with `can_hold` in the name
// cargo test -- --ignored // run tests marked #[ignore]
// cargo test -- --include-ignore // run all tests including ones marked #[ignore]

#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn can_hold(&self, other: &Rectangle) -> bool {
        self.width > other.width && self.height > other.height
    }
}

pub fn add(left: usize, right: usize) -> usize {
    left + right
}

pub fn greet(name: &str) -> String {
    format!("Hello, {}!", name)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn eq_and_ne() {
        assert_eq!(add(1, 3), 4);
        assert_ne!(add(1, 3), 5);
    }

    #[test]
    #[should_panic(expected = "Panicing!")]
    fn test_should_panic() {
        panic!("Panicing!");
    }

    #[test]
    fn test_can_hold() {
        let larger = Rectangle {
            width: 8,
            height: 7,
        };
        let smaller = Rectangle {
            width: 6,
            height: 2,
        };
        assert!(larger.can_hold(&smaller));
        assert!(!smaller.can_hold(&larger));
    }

    #[test]
    fn test_greet_contain_name() {
        let result = greet("Lawrence");
        assert!(result.contains("Lawrence"));
    }

    #[test]
    #[ignore]
    fn test_greet_with_custom_failure_message() {
        let result = greet("Lawrence");
        assert!(
            result.contains("Rust"),
            "Greeting did not contain name, value was \"{}\"",
            result
        );
    }
}
