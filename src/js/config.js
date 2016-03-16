module.exports = 
  
  [
    {
      "type": "heading",
      "defaultValue": "Suit Up Configuration",
      "size": 3
    },
    {
      "type": "section",
      "items": [
        {
          "type": "heading",
          "defaultValue": "Colors"
        },
        /*
        {
          "type": "text",
          "defaultValue": "Currently available on the Pebble Chalk (PTR) platform."
        },
        */
        {
          "type": "color",
          "appKey": "BACKGROUND_KEY",
          "defaultValue": "FFFFFF",
          "label": "Background Color",
          "sunlight": true
        },
        {
          "type": "color",
          "appKey": "TIE_KEY",
          "defaultValue": "00FFFF",
          "label": "Tie Color",
          "sunlight": true
        },
        {
          "type": "color",
          "appKey": "COLLAR_KEY",
          "defaultValue": "555555",
          "label": "Collar Color",
          "sunlight": true
        }
     ]
  },
   
  {
  "type": "submit",
  "defaultValue": "Save"
  }
]