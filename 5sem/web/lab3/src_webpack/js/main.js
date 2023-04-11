var users;
 get_user_list = async function(){
    let answer = await fetch("/main", {method: "GET"});
    users = await answer.json();
    for(let i = 0; i < users.length; i++){
        let cur_user = users[i];
        let cur_user_html = "<tr>"+"<td><input type='checkbox' class='user_checkbox' name='user_checkbox' id='user_checkbox" + cur_user.id + "'></td>"+
            // "<td>" + cur_user.id + "</td>"+
            "<td><img style='width:10vw; height: 10vh;' src='/public/images/" + cur_user.photo + "'></td>"+
            "<td>" + cur_user.name + "</td>"+
            "<td>" + cur_user.mail + "</td>"+
            "<td>" + cur_user.birth + "</td>"+
            "<td>" + cur_user.status + "</td>"+
            "<td>" + cur_user.role + "</td>"+
            "</tr>";
        $("#user_table").append($(cur_user_html));
    }
}

$(document).ready(()=>{
    get_user_list();
});

selected_user = function (){
    let check = $(".user_checkbox");
    for(let i = 0; i < check.length; i++) if(check[i].checked) return i;
    return -1;
}

open_edit = function(){
    let check = selected_user();
    if(check == -1) alert("Can`t edit. Please, choose user");
    else{
        $("#name_textbox").prop("value", users[check].name);
        $("#date_textbox").datepicker("setDate", users[check].birth);
        $("#email_textbox").prop("value", users[check].mail);
        $("#role").prop("value", users[check].role);
        $("#status").prop("value", users[check].status);
        $("#edit_dialog").prop("open", true);
    }
}

 update = async function(){
    let answer = await fetch("/",{method:"GET"});
    document.open();
    document.write(await answer.text());
    document.close();
}

edit_user = async function(){
    let answer = await fetch("/users/" + selected_user(),
        {method: "PUT",
            headers:{"content-type": "application/json;charset=utf-8"},
            body: JSON.stringify({name: $("#name_textbox").prop("value"), birth: $("#date_textbox").prop("value"), mail: $("#email_textbox").prop("value"), role: $("#role").prop("value"), status: $("#status").prop("value")})
        });
    await update();
}

open_info = function() {
    let check = selected_user();
    if(check == -1) alert("Can`t show info. Please, choose user");
    else window.location = '/info/' + selected_user();
}