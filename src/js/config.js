module.exports = 
  
  [
    {
      "type": "heading",
      "defaultValue": "Dapper Configuration",
      "size": 3
    },
    {
      "type": "section",
      "items": [
        {
          "type": "heading",
          "defaultValue": "Color Settings"
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
          "label": "Background",
          "sunlight": true
        },
        
        {
          "type": "color",
          "appKey": "COLLAR_KEY",
          "defaultValue": "555555",
          "label": "Collar",
          "sunlight": true
        },
        
        {
          "type": "color",
          "appKey": "TIE_KEY",
          "defaultValue": "00FFFF",
          "label": "Tie",
          "sunlight": true
        }
     ]
  },
   
  {
  "type": "submit",
  "defaultValue": "Save"
  }
]