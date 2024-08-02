
fn passer_url(url:&str) -> String {
    let offer_url=url;
    offer_url.to_string()
}

fn main(){
    let url = "https://www.rust-lang.org/";
    let url = passer_url(url);
    println!("url: {}", url);
}