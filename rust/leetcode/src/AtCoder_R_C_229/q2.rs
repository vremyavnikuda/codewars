use std::io::{self, Read, Write};

fn main() {
    let mut q1 = String::new();
    io::stdin().read_to_string(&mut q1).unwrap();
    let mut q2 = q1.split_ascii_whitespace().map(|a1| a1.parse::<i64>().unwrap());
    let q3 = io::stdout();
    let mut q4 = io::BufWriter::new(q3.lock());
    let q5 = q2.next().unwrap();
    for _ in 0..q5 {
        let q6 = q2.next().unwrap();
        let (mut q7, mut q8, mut q9) = (0i64, 0i64, true);
        for a2 in 0..q6 {
            let a3 = q2.next().unwrap();
            if a2 > 0 {
                let a4 = q7 - 2 * a3;
                if a4 < 0 {
                    q9 = false;
                } else {
                    q8 = q8.max(a4);
                }
            }
            q7 = a3;
        }
        let a5 = if !q9 {
            -1
        } else if q7 > 0 {
            q8.max(1)
        } else {
            q8
        };
        writeln!(q4, "{}", a5).unwrap();
    }
}
