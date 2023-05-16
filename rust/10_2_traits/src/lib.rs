// a type's behavior consists of methods we can call
// trait definitions are a way to group method signature together
pub trait Summary {
    fn summarize_author(&self) -> String;

    fn summarize(&self) -> String {
        format!("(Read more from {}...)", self.summarize_author())
    }
}

pub struct NewsArticel {
    pub headline: String,
    pub location: String,
    pub author : String,
    pub content: String,
}

impl Summary for NewsArticel {
    fn summarize_author(&self) -> String {
        format!("@{}", self.author)
    }
}

pub struct Tweet {
    pub username: String,
    pub content: String,
    pub reply: bool,
    pub retweet: bool,
}

impl Summary for Tweet {
    fn summarize(&self) -> String {
        format!("{}: {}", self.username, self.content)
    }

    fn summarize_author(&self) -> String {
        format!("@{}", self.username)
    }
}

// trait bound syntax:
// pub fn notify<T: Summary>(item: &T) {...
pub fn notify(item: &impl Summary) {
    println!("Breaking news! {}", item.summarize());
}

/* example of function notify with two params
 * with `impl Trait` syntax:
 * pub fn notify(item1: &impl Summary, item2: &impl Summary) {
 *
 * with trait bound syntax:
 * pub fn notify<T: Summary>(item1: &T, item2: &T) {
 *
 * speifying multiple trait bounds:
 * pub fn notify(item: &(impl Summary + Display)) {
 * pub fn notify<T: Summary + Display>(item: &T) {
 *
 * using `where` clause when there's too many trait bounds:
 * fn some_func<T: Display + Clone, U: Clone + Debug>(t: &T, u: &U) -> i32 {
 * fn some_func<T, U>(t: &T, u: &U) -> i32
 * where
 *     T: Display + Clone,
 *     U: Clone + Debug,
 * {
 */
