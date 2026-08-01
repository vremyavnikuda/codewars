impl Solution {
    pub fn paths_with_max_score(board: Vec<String>) -> Vec<i32> {
        let q1 = board.len();
        let q2: i64 = 1_000_000_007;
        let ix = |a1: usize, a2: usize| a1 * q1 + a2;
        let mut q3 = vec![-1i64; q1 * q1];
        let mut q4 = vec![0i64; q1 * q1];
        q3[ix(q1 - 1, q1 - 1)] = 0;
        q4[ix(q1 - 1, q1 - 1)] = 1;
        fn upd(
            q1: usize,
            b1: usize,
            b2: usize,
            b3: usize,
            b4: usize,
            board: &[String],
            q3: &mut [i64],
            q4: &mut [i64],
            q2: i64,
        ) {
            if b3 >= q1 || b4 >= q1 {
                return;
            }
            let ix = |a1: usize, a2: usize| a1 * q1 + a2;
            let c1 = board[b1].as_bytes()[b2] as char;
            if q3[ix(b3, b4)] == -1 || "XS".contains(c1) {
                return;
            }
            if q3[ix(b3, b4)] > q3[ix(b1, b2)] {
                q3[ix(b1, b2)] = q3[ix(b3, b4)];
                q4[ix(b1, b2)] = q4[ix(b3, b4)];
            } else if q3[ix(b3, b4)] == q3[ix(b1, b2)] {
                q4[ix(b1, b2)] = (q4[ix(b1, b2)] + q4[ix(b3, b4)]) % q2;
            }
        }
        for b1 in (0..q1).rev() {
            for b2 in (0..q1).rev() {
                upd(q1, b1, b2, b1 + 1, b2, &board, &mut q3, &mut q4, q2);
                upd(q1, b1, b2, b1, b2 + 1, &board, &mut q3, &mut q4, q2);
                upd(q1, b1, b2, b1 + 1, b2 + 1, &board, &mut q3, &mut q4, q2);
                let c2 = board[b1].as_bytes()[b2] as char;
                if q3[ix(b1, b2)] != -1 && c2.is_ascii_digit() {
                    q3[ix(b1, b2)] += c2 as i64 - '0' as i64;
                }
            }
        }
        let mut a1 = vec![0i32; 2];
        if q3[ix(0, 0)] != -1 {
            a1[0] = q3[ix(0, 0)] as i32;
            a1[1] = q4[ix(0, 0)] as i32;
        }
        a1
    }
}
