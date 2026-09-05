use std::io::{self, Read, Write};

fn main() {
    let mut q1 = String::new();
    io::stdin().read_to_string(&mut q1).unwrap();
    let mut q2 = q1
        .split_ascii_whitespace()
        .map(|a1| a1.parse::<i64>().unwrap());
    let q3 = io::stdout();
    let mut q4 = io::BufWriter::new(q3.lock());
    for _ in 0..q2.next().unwrap() {
        let q5 = q2.next().unwrap();
        let (mut q6, mut q7, mut q8, mut q9) = (0i64, 0i64, 0i64, 0i64);
        let (mut q10, mut q11, mut q12) = (0i64, 0i64, 0i64);
        for _ in 0..q5 {
            let a2 = q2.next().unwrap();
            q12 += a2;
            if a2 % 2 == 1 {
                q10 += 1;
                if a2 > q6 {
                    q7 = q6;
                    q6 = a2;
                } else if a2 > q7 {
                    q7 = a2;
                }
            } else {
                q11 += 1;
                if a2 > q8 {
                    q9 = q8;
                    q8 = a2;
                } else if a2 > q9 {
                    q9 = a2;
                }
            }
        }
        let mut q13 = i64::MIN;
        if q10 >= 2 {
            q13 = q13.max(q6 + q7 + 2 * q11.min(q10 - 1));
        }
        if q11 >= 2 {
            q13 = q13.max(q8 + q9 + 2 * q10.min(q11 - 1));
        }
        if q10 >= 1 && q11 >= 1 {
            q13 = q13.max(q6 + q8 + 2 * q10.min(q11) - 1);
        }
        writeln!(q4, "{}", (2 * q12 - q13) / 2).unwrap();
    }
}
