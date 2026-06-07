use std::env;

fn main() {
    let mut args = env::args();
    if args.len() < 2 {
        // help message
        if let Some(program_name) = args.nth_back(0) {
            println!("Usage: {} [api key] [target]", program_name);
        } else {
            println!("Usage: program [api key] [target]");
        }
    }

    args.next(); // skip program name
    for arg in args {
        match arg.as_str() {
            "--help"    => println!("Help Argument found!"),
            "--version" => println!("Display version"),
        }
    }
}
