var mqtt = require('mqtt')
var client = mqtt.connect('mqtt://localhost:1884')
var topic = '8dbe2cf3ceb9ee8998aa752e23aca2d5'

client.on('message', (topic, message)=>{
    message = message.toString()
    console.log(message)
})

client.on('connect', ()=>{
    client.subscribe(topic)
})