var mqtt = require('mqtt')
var client = mqtt.connect('mqtt://localhost:1884')
var topic = 'LINTANGtest123'
var message = 'Hello World!'

client.on('connect', ()=>{
        client.publish(topic, message)
        console.log('Message sent!', message)
})
console.log("bareeev");