var user;
var friends;
async function get_user(){
    let answer = await fetch("/main/" + window.location.href.substr(window.location.href.lastIndexOf('/') + 1), {method: "GET"});
    user = await answer.json();
    console.log(user);
    let user_html = "<tr>"+"<td><img style='width:10vw; height: 15vh;' src='/public/images/" + user.photo + "'></td>"+
        "<td>" + user.name + "</td>" + "</tr>";
    $(".info_table").append($(user_html));
}

async function get_friends(){
    let answer = await fetch("/info_data/" + window.location.href.substr(window.location.href.lastIndexOf('/') + 1), {method: "GET"});
    friends = await answer.json();
    console.log(friends);
    for(let i = 0; i < friends.length; i++){
        let cur_user = friends[i];
        let cur_user_html = "<tr>"+"<td><img style='width:10vw; height: 10vh;' src='/public/images/" + cur_user.photo + "'></td>"+
            "<td>" + cur_user.name + "</td>"+
            "<td>" + cur_user.mail + "</td>"+
            "<td>" + cur_user.birth + "</td>"+
            "<td>" + cur_user.status + "</td>"+
            "<td>" + cur_user.role + "</td>"+
            "</tr>";
        $(".friend_table").append($(cur_user_html));
    }
}
$(document).ready(()=>{get_user(); get_friends();});

