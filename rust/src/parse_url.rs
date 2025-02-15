use std::io::BufRead;

#[allow(dead_code)]
pub(crate) fn main() {
    let stdin = std::io::stdin();
    let input = stdin.lock().lines().next().unwrap().unwrap();

    let parse_url: Vec<&str> = input.split("://").collect();
    let parse_url_start = parse_url[0];
    let parse_url_end = parse_url[1];
    
    let host_end = parse_url_end.find('/').unwrap_or(parse_url_end.len());
    let host = &parse_url_end[..host_end];
    let rest = &parse_url_end[host_end..];
    
    let (handle, params) = if let Some(question_pos) = rest.find('?') {
        (&rest[1..question_pos], &rest[question_pos + 1..])
    } else {
        (&rest[1..], "")
    };
    
    println!("Proto: {}", parse_url_start);
    println!("Host: {}", host.trim_end_matches('/'));
    
    if !handle.is_empty() {
        println!("Handle: {}", handle.trim_matches('/'));
    }
    
    if !params.is_empty() {
        for param in params.split('&').rev() {
            let kv: Vec<&str> = param.split('=').collect();
            if kv.len() == 2 {
                println!("{} -> {}", kv[0], kv[1]);
            }
        }
    }
}