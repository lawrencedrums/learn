// Crate can be either:
// binary crate - 
//     programs you can compile to an executable that you can run
//     must have a `main` function that defines what happens when it runs
//     like a command-line program or a server
// library crate -
//     does NOT have a `main` function
//     does NOT compile into an executable
//     define functionality intended to be shared  with multiple projects
//     like the `rand` crate (like a library in other languages)
//
//
// Package is a bundle of one or more crates (as many as you want),
// it contains a `Cargo.toml` that describes how to build those crates
// 
// `Cargo` is actually a package that contains the binary crate for the
// command-line tool when you build your code
// 
// The Cargo package also contains a library crate that the binary crates
// depends on
//
//
// Module cheat sheet
// - Start from the crate root
// usually `src/lib.rs` for a library crate, `src/main.rs` for binary
// 
// - Declaring modules
// say you declare a "garden" module with `mod garden`, the compiler will look
// 1. inline, within curly brackets that replace the semicolon following
//    `mod garden`
// 2. in the file `src/garden.rs`
// 3. in the file `src/garden/mod.rs`
//
// - Paths to code in modules
// you can refer to code in the module from anywhere else in that same crate
// an `Asparagus` type in the garden vegetable module would be found at 
// `crate::garden::vegetable::Asparagus`
//
// - private vs public
// code within a module is private by default
// declare module as public with `pub mod` instead of `mod`
//
// - `use` keyword
// creates shortcut to items
// `usse crate::garden::vegetables::Asparagus`, and then you only need to write
// `Asparagus` to make use of that type in the scope

use crate::garden::vegetables::Asparagus;

pub mod garden;

fn main() {
    let plant = Asparagus {};
    println!("I'm growing {:?}!", plant);
}
