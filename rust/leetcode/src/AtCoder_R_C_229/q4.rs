use std::io::{self, Read, Write};

fn main() {
    let mut q1 = String::new();
    stdin().read_to_string(&mut q1).unwrap();
    let mut q2 = q1
        .split_ascii_whitespace()
        .map(|a1| a1.parse::<i64>().unwrap());
    let q3 = io::stdout();
    let mut q4 = io::BufWriter::new(q3.lock());
    for _ in 0..q2.next().unwrap() {
        let q5 = q2.next().unwrap();
        let (q6, q7) = (0..=q5).fold((0i64, i64::MAX), |(a2, a3), _| {
            let a4 = q2.next().unwrap();
            (a2 + a4, a3.min(a4))
        });
        let a5 = if q6 - q5 * (q5 + 1) * (q7 / q5) >= q5 {
            "Alice"
        } else {
            "Bob"
        };
        writeln!(q4, "{}", a5).unwrap();
    }
}
