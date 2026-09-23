// Wraps every standalone LeetCode snippet in src/<dir>/*.rs into its own module,
// so files stay paste-ready for LeetCode while rust-analyzer/cargo still see them.
// Solution/TreeNode/ListNode come in via glob imports, so a file's own definitions win.
use std::{env, fmt::Write, fs, path::Path};

// ponytail: archived set has its own lib.rs/main.rs and is not wired in
const SKIP: &[&str] = &["offer_task_leetcode"];

fn ident(s: &str) -> String {
    let s: String = s.chars().map(|c| if c.is_ascii_alphanumeric() { c } else { '_' }).collect();
    if s.starts_with(|c: char| c.is_ascii_digit()) { format!("_{s}") } else { s }
}

fn main() {
    let src = Path::new(&env::var("CARGO_MANIFEST_DIR").unwrap()).join("src");
    println!("cargo:rerun-if-changed=src");
    let mut dirs: Vec<_> = fs::read_dir(&src).unwrap().flatten().map(|e| e.path()).filter(|p| p.is_dir()).collect();
    dirs.sort();
    let mut out = String::new();
    for dir in dirs {
        let name = dir.file_name().unwrap().to_str().unwrap().to_owned();
        if SKIP.contains(&name.as_str()) {
            continue;
        }
        println!("cargo:rerun-if-changed={}", dir.display());
        let mut files: Vec<_> = fs::read_dir(&dir).unwrap().flatten().map(|e| e.path())
            .filter(|p| p.extension().is_some_and(|e| e == "rs")).collect();
        if files.is_empty() {
            continue;
        }
        files.sort();
        writeln!(out, "pub mod {} {{", ident(&name)).unwrap();
        for f in files {
            let path = f.display().to_string().replace('\\', "/");
            writeln!(
                out,
                "    pub mod {0} {{ pub struct Solution; pub mod {0} {{ #[allow(unused_imports)] use {{crate::prelude::*, super::*}}; include!(\"{path}\"); }} }}",
                ident(f.file_stem().unwrap().to_str().unwrap())
            )
            .unwrap();
        }
        writeln!(out, "}}").unwrap();
    }
    fs::write(Path::new(&env::var("OUT_DIR").unwrap()).join("mods.rs"), out).unwrap();
}
