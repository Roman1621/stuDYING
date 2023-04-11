function edit_storage(text){
    let previous_filter_index = get_filter_option_index();
    document.open();
    document.write(text);
    document.close();
    document.getElementById("filter_select").selectedIndex = previous_filter_index;
}
async function add_book(){
    let answer = await fetch("/groups", {
        method: "POST",
        headers: {
            "filter": get_filter_option(),
            "filter_value": document.getElementById("filter_input")
        }});
    edit_storage(await answer.text())
}

function get_filter_option(){
    let filter = document.getElementById("filter_select")
    return filter.options[filter.selectedIndex].value
}
function get_filter_option_index(){
    let filter = document.getElementById("filter_select")
    return filter.selectedIndex
}
function change_filter(){
    switch (get_filter_option()){
        case "none":
        case "availability":
        case "unavailable":
            document.getElementById("filter_input").type = "hidden";
            break;
        case "return_date":
            document.getElementById("filter_input").type = "date";
            break;
    }
}
async function update(){
    let answer = await fetch("/",{
        method: "GET",
        headers: {
            "filter": get_filter_option(),
            "filter_value": document.getElementById("filter_input").value
        }
    });
    let deb = await answer.text()
    //console.log(deb)
    edit_storage(deb);
}

function edit_book(){
    for(let i = 0; i < document.getElementsByTagName("input").length; i++){
        if(document.getElementsByTagName("input")[i].id.indexOf("cur_book") === 0 && document.getElementsByTagName("input")[i].checked){
            window.location = "/groups/" + document.getElementsByTagName("input")[i].id.slice("cur_book_".length);
            break;
        }
    }
}

function open_remove_confirm_dialog(){
     document.getElementById("remove_dialog").open = true
}
function close_dialog(){
    document.getElementById("remove_dialog").removeAttribute("open")
}


async function delete_book() {
    let remove_book_list = [];
    for (let i = 0; i < document.getElementsByTagName("input").length; i++) {
        if (document.getElementsByTagName("input")[i].id.indexOf("cur_book") === 0 && document.getElementsByTagName("input")[i].checked) {
            //console.log(document.getElementsByTagName("input")[i].id);
            remove_book_list.push(document.getElementsByTagName("input")[i].id.split("_")[2]);
        }
    }
    let answer = await fetch("/groups/", {
        method: "DELETE",
        headers: {
            remove_list: remove_book_list,
            "filter": get_filter_option(),
            "filter_value": document.getElementById("filter_input").value,
            "content-type": "application/json;charset=utf-8"
        }
    });
    let deb = await answer.text()
    //console.log(deb)
    edit_storage(deb)
}