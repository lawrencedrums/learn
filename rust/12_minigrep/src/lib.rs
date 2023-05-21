use std::env;
use std::error::Error;
use std::fs;

pub struct Config {
    pub query: String,
    pub file_path: String,
    pub ignore_case: bool,
}

impl Config {
    pub fn build(
        mut args: impl Iterator<Item = String>
    ) -> Result<Config, &'static str> {
        args.next();

        let query = match args.next() {
            Some(arg) => arg,
            None => return Err("No query string provided!"),
        };

        let file_path = match args.next() {
            Some(arg) => arg,
            None => return Err("No file path provided!"),
        };

        let ignore_case = env::var("IGNORE_CASE").is_ok();

        Ok(Config {
            query,
            file_path,
            ignore_case,
        })
    }
}

pub fn run(config: Config) -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string(config.file_path)?;

    let results = if config.ignore_case {
        search_case_insensitive(&config.query, &contents)
    } else {
        search(&config.query, &contents)
    };

    for line in results {
        println!("{line}");
    }

    Ok(())
}

pub fn search<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
    contents
        .lines()
        .filter(|line| line.contains(query))
        .collect()
}

pub fn search_case_insensitive<'a>(
    query: &str,
    contents: &'a str
) -> Vec<&'a str> {
    let query = query.to_lowercase();

    contents
        .lines()
        .filter(|line| line.to_lowercase().contains(&query))
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_search_one_result() {
        let query = "wings";
        let contents = "\
Just you imagine the damage that's done
when you fly with wax wings in the sun.
The machine is turning me";

        assert_eq!(
            vec!["when you fly with wax wings in the sun."],
            search(query, contents)
        );
    }

    #[test]
    fn test_case_insensitive_search() {
        let query = "rogue";
        let contents = "\
The Rogue is an adaptable, agile warrior
who can specialize in ranged
or close quarters combat.";

        assert_eq!(
            vec!["The Rogue is an adaptable, agile warrior"],
            search_case_insensitive(query, contents)
        );
    }
}
