use traits::{Summary, Tweet, NewsArticel};

fn main() {
    let tweet = Tweet {
        username: String::from("elon_musk"),
        content: String::from("Should I buy Twitter?"),
        reply: false,
        retweet: false,
    };
    println!("1 new tweet: {}", tweet.summarize());

    let news_article = NewsArticel {
        headline: String::from("Elon Musk bought Twitter for $43 billion"),
        location: String::from("Austin, TX, USA"),
        author: String::from("Some Asian"),
        content: String::from(
            "Tesla, SpaceX ,and Neurolink founder Elon Musk bought the social \
             media giant Twitter for $43 billion in unprecedented deal.",
        ),
    };
    println!("New article available! {}", news_article.summarize());
}

fn returns_summarizable() -> impl Summary {
    Tweet {
        username: String::from("nwjns"),
        content: String::from("Oh my oh my god"),
        reply: false,
        retweet: false,
    }
}
