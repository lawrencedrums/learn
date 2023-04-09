use std::collections::HashMap;

enum SpreadsheetCell {
    Int(i32),
    Float(f64),
    Text(String),
}

fn main() {
    // let mut v: Vec<i32> = Vec::new();
    let mut v = vec![1, 1, 2, 3, 5, 8];
    v.push(13);

    // accessing elements
    let &third = &v[2]; // panics when index exceed length
    println!("Third element: {third}");

    // handles index out of range
    let third: Option<&i32> = v.get(2);
    match third {
        Some(third) => println!("Third element: {third}"),
        None => println!("No Third element!"),
    }

    // iterating
    for i in &v {
        println!("{i}");
    }
    // iterating with changes
    for i in &mut v {
        *i += 10; // * dereference i to get the value
    }

    let row = vec![
        SpreadsheetCell::Int(3),
        SpreadsheetCell::Float(10.12),
        SpreadsheetCell::Text(String::from("wine")),
    ];

    // string
    // let mut s = String::new();
    let data = "initial contests";
    let s = data.to_string();
    // or
    // let s = "initial contests".to_string();
    // let s = String::from("initial contents");
    
    let mut s1 = String::from("fuzz");
    s1.push(' ');
    s1.push_str("buzz"); // push/push_str doesn't take ownership
    println!("{s1}");

    let s2 = String::from("is a fun problem.");
    let s3 = s1 + &s2; // s1 has been moved, can no longer be used
    // let formatted_s3 = format!("{s1} - {s2}");
    
    // no string indexing support in Rust
    let slice = &s3[0..4];

    // iterating over strings
    for c in slice.chars() { // .bytes() will return each raw byte
        println!("{c}");
    }

    let mut scores = HashMap::new();
    scores.insert(String::from("FaZe"), 2);
    scores.insert(String::from("Navi"), 3);
    scores.insert(String::from("G2"), 0);
    scores.insert(String::from("G2"), 1); // overwrite a value
    scores.entry(String::from("Liquid")).or_insert(0); 

    let score = scores.get("FaZe").copied().unwrap_or(0);
    for (k, v) in &scores {
        if v == &score {
            println!("{k}");
        } else {
            println!("{v}");
        }
    }
    
    let text = "sorry not sorry cant stop wont stop";
    let mut word_count = HashMap::new();
    for word in text.split_whitespace() {
        let count = word_count.entry(word).or_insert(0);
        *count += 1;
    }
    println!("{:?}", word_count);
}
