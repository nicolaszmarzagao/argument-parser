use std::env;

#[derive(Debug)]
struct Config {
    name: String,
    count: i32
}

impl Config {
    fn new() -> Self {
        Config { name: "null".to_string() , count: 1 }
    }
}

fn main() {
    let mut args = env::args();
    if args.len() < 2 {
        // help message else is if the program name is not found (which should not happen)
        if let Some(program_name) = args.nth(0) {
            println!("Usage: {} --name <name> --count <count>", program_name);
            return;
        } else {
            println!("Usage: program --name <name> --count <count>");
            return;
        }
    }

    let args: Vec<String> = std::env::args().skip(1).collect();
    let mut config: Config = Config::new();

    for (index, arg) in args.iter().enumerate() {
        match arg.as_str() {
            "-n" | "--name" => {
                if let Some(name) = args.get(index+1) {
                    config.name = name.to_string();
                }
            }

            "-c" | "--count" => {
                if let Some(count) = args.get(index+1) {
                    config.count = count.parse().unwrap();
                }
            }

            "-h" | "--help" => println!("Help message"),

            _ => {}
        }
    }

    // instead of imediatly acting on the flags, I need to gather them, then decide behavior
    for _i in 0..config.count {
        println!("Hello {}!", config.name);
    }
}
