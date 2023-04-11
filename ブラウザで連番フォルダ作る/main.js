"use strict";

{
  //ファイルに使用できない記号を置換する関数
  const filenameReplace = function (targetString) {
    let string = targetString;
    //ウィンドウズのファイル名で使用できない記号
    let marks = ["\\", '/', ':', '*', '?', "<", ">", '|'];

    //全部置き換えて消す
    marks.forEach(function (element) {
      string = string.replace(element, 'ぬ')
    });
    return string;
  };


  // ここをメインの処理とする
  let saveButton = document.getElementById("save-button");
  saveButton.addEventListener("click", () => {

    //ーーーーーーーーーー入力された値を読み込むーーーーーーーーーー
    let inputName = document.getElementById("folder-name");
    let folderName = filenameReplace(inputName.value); //呼び出しと同時にやばい記号置換

    let selectedFolderType = document.getElementById("select-type");
    let folderType = selectedFolderType.value;
    console.log(folderType);

    let inputStartNum = document.getElementById("start-number");
    let inputEndNum = document.getElementById("end-number");

    //注意：inputのtypeが「number」だとisNaNがうまくできないので注意
    //「number」だと文字列は全部「0」に変換されるため
    let startNum = Number(inputStartNum.value);
    let endNum = Number(inputEndNum.value);
    console.log(isNaN(inputEndNum.value));

    //ーーーーーーーーーーZIPファイルを作成するーーーーーーーーーー

    if (Number.isNaN(startNum) || Number.isNaN(endNum)) {
      alert("エラー：開始の数か終了の数に\n数字以外の値が入力されてる");
    }
    else if (endNum <= startNum) {
      alert("エラー：開始の数が終了の数より大きい！");
      console.log(`${endNum} <= ${startNum}`);
    }
    else if (startNum < 0) {
      alert("エラー：開始の数が0未満になっている！");
    }
    else if (1000 < endNum) {
      alert("セーフティ：連番の数が1000以上です!\nこれで作りたい場合は自己責任でコード書き換えてください)");
    }
    else {

      let zip = new JSZip(); ///「jszip.min.js」の機能→保存したいファイル作る

      for (let i = startNum; i <= endNum; i++) {
        const nowPass = folderType.replace("名前", folderName).replace("数字", i);
        zip.file(`${nowPass}/保持用.txt`, "あ");
      }

      //ブラウザで保存する処理(compressionはSTOREにして無圧縮にする。DEFLATEだと圧縮になる)
      zip.generateAsync({ type: "blob", compression: 'STORE' })
        .then(function (content) {
          saveAs(content, `${folderName}.zip`);
        });
    }
  });

}