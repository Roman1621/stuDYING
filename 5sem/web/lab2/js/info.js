function edit_storage(text) {
    document.open();
    document.write(text);
    document.close();
}
function go_back(){
    window.location = "/";
}

function get_book_id(){
    return window.location.href.substr(window.location.href.lastIndexOf("/") + 1);
}
async function give(){
    //document.getElementById("reader_textbox").value = document.getElementById("cur_reader").innerHTML;
    //document.getElementById("return_textbox").value = document.getElementById("return_date").innerHTML;
    let answer = await fetch("/groups/give/" + get_book_id(), {
        method: "POST"
        //body: JSON.stringify({cur_reader: document.getElementById("reader_textbox").value, return_date: document.getElementById("return_textbox").value})
    });
    let deb = await answer.text();
    //console.log(deb);
    edit_storage(deb);
}
async function reader(){
    let answer = await fetch("/groups/return/" + get_book_id(), {
        method: "POST"
    });
    let deb = await answer.text();
    edit_storage(deb);
}

function open_edit(){
    document.getElementById("title_textbox").value = document.getElementById("title_info").innerHTML;
    document.getElementById("author_textbox").value = document.getElementById("author_info").innerHTML;
    document.getElementById("release_textbox").value = document.getElementById("release_info").innerHTML;
    document.getElementById("reader_textbox").value = document.getElementById("cur_reader_info").innerHTML;
    document.getElementById("return_textbox").value = document.getElementById("return_date_info").innerHTML;
    document.getElementById("edit_dialog").open = true;
}
function cancel(){
    document.getElementById("edit_dialog").removeAttribute("open")
}
async function edit(){
    let answer = await fetch("/groups/edit/" + get_book_id(), {
        method: "POST",
        headers: {
            "content-type": "application/json;charset=utf-8"
        },
        body: JSON.stringify({title: document.getElementById("title_textbox").value, author: document.getElementById("author_textbox").value, release: document.getElementById("release_textbox").value, cur_reader: document.getElementById("reader_textbox").value, return_date: document.getElementById("return_textbox").value})
    });
    let deb = await answer.text();
    //console.log(document.getElementById("title_textbox").value);
    // console.log(deb);
    edit_storage(deb);
}
