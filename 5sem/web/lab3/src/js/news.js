var user;
var news;
async function get_news_list(){
    let answer = await fetch("/main", {method: "GET"});
    users = await answer.json();
    answer = await fetch("/news_data", {method:"GET"});
    news = await answer.json();
    for(let i = 0; i < news.length; i++){
        let cur_news = news[i];
        let cur_user = users[news[i].id_user];
        let cur_news_html = "<tr>"+
            "<td><img style='width:8vw; height: 8vh;' src='/public/images/" + cur_user.photo + "'></td>"+
            "<td>" + cur_user.name + "</td>"+
            "<td>" + cur_news.news_name + "</td>"+
            "<td>" + cur_news.news_body + "</td>"+
            "<td>" + cur_news.news_date + "</td>"
            "</tr>";
        $(".news_table").append($(cur_news_html));
    }
}

// async function get_news(){
//     let answer = await fetch("/news_data/" + window.location.href.substr(window.location.href.lastIndexOf('/') + 1), {method: "GET"});
//     news = await answer.json();
//     console.log(news);
//     for(let i = 0; i < news.length; i++){
//         let cur_news = news[i];
//         let cur_news_html = "<td>" + cur_news.news_name + "</td>"+
//             "<td>" + cur_news.news_body + "</td>"+
//             "<td>" + cur_news.news_date + "</td>"
//         $(".news_table").append($(cur_news_html));
//     }
// }

$(document).ready(()=>{get_news_list()});