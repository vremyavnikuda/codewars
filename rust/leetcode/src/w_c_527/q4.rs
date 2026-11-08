impl Solution {
    pub fn count_suffix(nums: Vec<i32>, target: Vec<i32>) -> Vec<i32> {
        let (n, m) = (nums.len(), target.len());
        let s: Vec<i32> = nums
            .iter()
            .copied()
            .chain([-1])
            .chain(target.iter().copied())
            .collect();
        let len = s.len();
        let mut z = vec![0usize; len];
        let (mut l, mut r) = (0, 0);
        for i in 1..len {
            if i < r {
                z[i] = z[i - l].min(r - i);
            }
            while i + z[i] < len && s[z[i]] == s[i + z[i]] {
                z[i] += 1;
            }
            if i + z[i] > r {
                l = i;
                r = i + z[i];
            }
        }
        let mut run = vec![0usize; m];
        for j in 1..m {
            run[j] = if target[j - 1] >= target[j] {
                run[j - 1]
            } else {
                j
            };
        }
        let mut diff = vec![0i32; 100_001];
        let mut nz = 0i32;
        let add = |diff: &mut Vec<i32>, nz: &mut i32, x: i32, d: i32| {
            let c = &mut diff[x as usize];
            *nz -= (*c != 0) as i32;
            *c += d;
            *nz += (*c != 0) as i32;
        };
        for &x in &nums {
            add(&mut diff, &mut nz, x, 1);
        }
        for &x in &target[..n] {
            add(&mut diff, &mut nz, x, -1);
        }
        let mut ans = Vec::with_capacity(m - n + 1);
        for k in 0..=m - n {
            if k > 0 {
                add(&mut diff, &mut nz, target[k - 1], 1);
                add(&mut diff, &mut nz, target[k + n - 1], -1);
            }
            let p = z[n + 1 + k].min(n - 1);
            let q = run[k + n - 1].max(k) - k;
            ans.push(if nz == 0 && q <= p {
                (p - q + 1) as i32
            } else {
                0
            });
        }
        ans
    }
}
