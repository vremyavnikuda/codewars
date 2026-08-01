pub struct Solution;

impl Solution {
    pub fn max_active_sections_after_trade(s: String, queries: Vec<Vec<i32>>) -> Vec<i32> {
        let q1 = s.as_bytes();
        let q2 = q1.len();
        let q3 = q1.iter().filter(|q4| **q4 == b'1').count() as i32;
        if !q1.contains(&b'0') {
            return vec![q3; queries.len()];
        }
        let mut q4: Vec<(usize, usize)> = Vec::new();
        let mut q5 = Vec::with_capacity(q2);
        for q6 in 0..q2 {
            if q1[q6] == b'0' {
                if q6 > 0 && q1[q6 - 1] == b'0' {
                    q4.last_mut().unwrap().1 += 1;
                } else {
                    q4.push((q6, 1usize));
                }
            }
            q5.push(q4.len() as isize - 1);
        }
        let q6 = q4.len();
        let q7 = q6.saturating_sub(1);
        let q8 = if q7 == 0 {
            0
        } else {
            usize::BITS as usize - q7.leading_zeros() as usize
        };
        let mut q9 = vec![0; q7 * q8];
        for qa in 0..q7 {
            q9[qa] = (q4[qa].1 + q4[qa + 1].1) as i32;
        }
        for qa in 1..q8 {
            let qb = 1usize << (qa - 1);
            let qc = 1usize << qa;
            for qd in 0..=q7 - qc {
                q9[qa * q7 + qd] = q9[(qa - 1) * q7 + qd].max(q9[(qa - 1) * q7 + qd + qb]);
            }
        }
        let qa = |qb: usize, qc: usize| -> i32 {
            let qd = qc.min(q7 - 1);
            if qb > qd {
                return 0;
            }
            let qe = usize::BITS as usize - (qd - qb + 1).leading_zeros() as usize - 1;
            let qf = 1usize << qe;
            q9[qe * q7 + qb].max(q9[qe * q7 + qd - qf + 1])
        };
        queries
            .into_iter()
            .map(|qb| {
                let qc = qb[0] as usize;
                let qd = qb[1] as usize;
                let qe = q5[qc];
                let qf = q5[qd];
                let qg = if qe == -1 {
                    -1
                } else {
                    let qh = qe as usize;
                    q4[qh].1 as i32 - (qc - q4[qh].0) as i32
                };
                let qh = if qf == -1 {
                    -1
                } else {
                    let qi = qf as usize;
                    (qd - q4[qi].0 + 1) as i32
                };
                let qi = qe + 1;
                let qj = (if q1[qd] == b'1' { qf } else { qf - 1 }) - 1;
                let qk = if q1[qd] == b'1' { qf } else { qf - 1 };
                let mut ql = q3;
                if q1[qc] == b'0' && q1[qd] == b'0' && qe + 1 == qf {
                    ql = ql.max(q3 + qg + qh);
                } else if qi <= qj {
                    ql = ql.max(q3 + qa(qi as usize, qj as usize));
                }
                if q1[qc] == b'0' && qe + 1 <= qk {
                    ql = ql.max(q3 + qg + q4[(qe + 1) as usize].1 as i32);
                }
                if q1[qd] == b'0' && qe < qf - 1 {
                    ql = ql.max(q3 + qh + q4[(qf - 1) as usize].1 as i32);
                }
                ql
            })
            .collect()
    }
}
