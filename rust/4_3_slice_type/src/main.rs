// Slices let you reference contiguous sequence of elements in a collection
// a slice is a kind of reference, therefore no ownership

fn main() {
    let s = String::from("Hello world!");
    let hello = first_word(&s);
    let mut world = &s[(hello+1)..];
    println!("{}", &s[..hello]);
    println!("{}", world);

    // s.clear(); // error!

    world = second_word(&s);
    println!("{}", world);

    let string_literal = "string literal";
    let which_word_is_it = second_word(&string_literal);
    println!("{}", which_word_is_it);

    // array slices!
    let a = [1, 2, 3, 4, 5];
    let array_slice = &a[1..3];
    assert_eq!(array_slice, &[2, 3]);
}

fn first_word(s: &String) -> usize {
    let bytes = s.as_bytes(); // convert our String into array of bytes

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' { // byte literal
            return i;
        }
    }
    
    s.len()
}

// better way of doing the above function
// return a slice type instead of starting and ending index
fn second_word(s: &str) -> &str { // &str = slice type
    let bytes = s.as_bytes();

    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[i+1..];
        }
    }

    &s[..]
}
