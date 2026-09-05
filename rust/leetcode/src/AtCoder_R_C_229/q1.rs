use std::io::{self, Read, Write};

fn main() {
    let mut q1 = String::new();
    stdin().read_to_string(&mut q1).unwrap();
    let q2: usize = q1.trim().parse().unwrap();
    let q3 = (1..=25).find(|a1| a1 * a1 >= q2).unwrap();
    let q4 = q2 / q3;
    let q5 = q2 % q3;
    let q6 = std::iter::repeat('A')
        .take(q5)
        .chain(std::iter::repeat('C').take(usize::from(q5 > 0)))
        .chain(std::iter::repeat('A').take(q3 - q5))
        .chain(std::iter::repeat('C').take(q4));
    let q7 = io::stdout();
    let mut q8 = io::BufWriter::new(q7.lock());
    for (a1, a2) in q6.enumerate() {
        if a1 > 0 {
            q8.write_all(b"R").unwrap();
        }
        write!(q8, "{}", a2).unwrap();
    }
    writeln!(q8).unwrap();
}
