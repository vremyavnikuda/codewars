#!/usr/bin/env rust-script

pub struct Solution;
impl Solution {
    pub fn count_unguarded(m: i32, n: i32, guards: Vec<Vec<i32>>, walls: Vec<Vec<i32>>) -> i32 {
        let mut q1 = vec![vec![0; n as usize]; m as usize];
        for q2 in &guards {
            q1[q2[0] as usize][q2[1] as usize] = 2;
        }
        for q3 in &walls {
            q1[q3[0] as usize][q3[1] as usize] = 2;
        }
        let q4 = [-1, 0, 1, 0];
        let q5 = [0, 1, 0, -1];
        for q6 in &guards {
            let q7 = q6[0] as usize;
            let q8 = q6[1] as usize;
            for q9 in 0..4 {
                let mut q10 = q7 as i32;
                let mut q11 = q8 as i32;
                let q12 = q4[q9];
                let q13 = q5[q9];
                while q10 + q12 >= 0
                    && q10 + q12 < m
                    && q11 + q13 >= 0
                    && q11 + q13 < n
                    && q1[(q10 + q12) as usize][(q11 + q13) as usize] < 2
                {
                    q10 += q12;
                    q11 += q13;
                    q1[q10 as usize][q11 as usize] = 1;
                }
            }
        }
        let mut q14 = 0;
        for q15 in 0..m as usize {
            for q16 in 0..n as usize {
                if q1[q15][q16] == 0 {
                    q14 += 1;
                }
            }
        }
        q14
    }
}

fn main() {
    let m = 4;
    let n = 6;
    let guards = vec![vec![0, 0], vec![1, 1], vec![2, 3]];
    let walls = vec![vec![0, 1], vec![2, 2], vec![1, 4]];
    println!("Input: m = {}, n = {}", m, n);
    println!("Guards: {:?}", guards);
    println!("Walls: {:?}", walls);
    println!("Result: {}", Solution::count_unguarded(m, n, guards, walls));
}
