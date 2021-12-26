autowatch = 1;

var tagsDict = new Dict;
var objDict = new Dict;
tagsDict.import_json("tags.json");
objDict.import_json("objects.json");


function getListOfObjects(tag) {
    if (tag == "all" || tag == "misc") {
        return objDict.getkeys();
    } else {
        var names = tagsDict.get(tag);

        // Hack: if there is only one element in the list,
        // it'll separate the name into a list of chars
        if (names[0] != 'a') {
            names.sort();
            return names;
        } else {
            var s = "";
            for (var i = 0; i < names.length; i++) {
                s += names[i];
            }
            return [s];
        }
    }
}

function setItems(tag) {
    var names = getListOfObjects(tag);
    outlet(0, ["clear", "all"]);
    for (var i = 0; i < names.length; i++) {
        outlet(0, ["set", 0, i, names[i]]);
        outlet(0, ["set", 1, i, objDict.get(names[i]).get("digest")]);
    }
}


// Figure out which help file to open given the clicked cell
function getHelp(col, row, name) {
    outlet(0, ["load", name + ".maxhelp"])
}

