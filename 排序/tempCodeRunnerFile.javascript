const url = "https://changjiang.yuketang.cn/";

const getInfos = "api/v3/activities/received/";

const data = {
    size : '1',
    type : [],
    beginTime : null,
    endTime : null
};

var sessionid = "jrzyp2ptndumaljfqe48zk1fgbuk6lxv";

fetch(url + getInfos, {
    method: 'POST',
    headers: {
        'Content-Type': 'application/json',
        'Cookie': 'sessionid=' + sessionid
    },
    body: JSON.stringify(data)
})
.then(response => response.json())
.then(datas => {
    console.log(datas);
})
.catch(error => {
    console.error('Error:', error);
});
