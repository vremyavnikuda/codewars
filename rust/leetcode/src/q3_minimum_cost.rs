impl Solution {
    pub fn minimum_cost(
        source: String,
        target: String,
        original: Vec<String>,
        changed: Vec<String>,
        cost: Vec<i32>,
    ) -> i64 {
        let n = source.len();
        if n != target.len() {
            return -1;
        }
        const I: i64 = (1_i64 << 60);
        struct N {
            c: [i32; 26],
            v: i32,
        }
        impl N {
            fn n() -> Self {
                Self { c: [-1; 26], v: -1 }
            }
        }
        fn i(w: &[u8], a: &mut Vec<N>, z: &mut i32) -> i32 {
            let mut p: usize = 0;
            for &b in w {
                let k = (b - b'a') as usize;
                let t = a[p].c[k];
                if t < 0 {
                    let id = a.len();
                    a[p].c[k] = id as i32;
                    a.push(N::n());
                    p = id;
                } else {
                    p = t as usize;
                }
            }
            if a[p].v < 0 {
                a[p].v = *z;
                *z += 1;
            }
            a[p].v
        }
        let m = cost.len();
        let mut g = vec![vec![I; m << 1]; m << 1];
        for i0 in 0..g.len() {
            g[i0][i0] = 0;
        }
        let mut a: Vec<N> = Vec::with_capacity(1 + (m << 1));
        a.push(N::n());
        let mut z: i32 = 0;
        for x in 0..m {
            let u = i(original[x].as_bytes(), &mut a, &mut z) as usize;
            let v = i(changed[x].as_bytes(), &mut a, &mut z) as usize;
            let w = cost[x] as i64;
            if w < g[u][v] {
                g[u][v] = w;
            }
        }
        let k0 = z as usize;
        for k in 0..k0 {
            for i0 in 0..k0 {
                let ik = g[i0][k];
                if ik >= I {
                    continue;
                }
                for j0 in 0..k0 {
                    let v = ik + g[k][j0];
                    if v < g[i0][j0] {
                        g[i0][j0] = v;
                    }
                }
            }
        }
        let s = source.as_bytes();
        let t = target.as_bytes();
        let mut d = vec![I; n + 1];
        d[n] = 0;
        for i0 in (0..n).rev() {
            let mut r = if s[i0] == t[i0] { d[i0 + 1] } else { I };
            let mut p: i32 = 0;
            let mut q: i32 = 0;
            for j in i0..n {
                let cp = a[p as usize].c[(s[j] - b'a') as usize];
                let cq = a[q as usize].c[(t[j] - b'a') as usize];
                if cp < 0 || cq < 0 {
                    break;
                }
                p = cp;
                q = cq;
                let pv = a[p as usize].v;
                let qv = a[q as usize].v;
                if pv < 0 || qv < 0 {
                    continue;
                }
                let w = g[pv as usize][qv as usize];
                if w < I {
                    let v = w + d[j + 1];
                    if v < r {
                        r = v;
                    }
                }
            }
            d[i0] = r;
        }
        if d[0] >= I { -1 } else { d[0] }
    }
}
