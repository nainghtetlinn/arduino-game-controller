// player A
const int playerA_abcPin = 34;
const int ledPinaa = 2;
const int ledPinab = 13;
const int ledPinac = 14;
// player B
const int playerB_abcPin = 32;
const int ledPinba = 25;
const int ledPinbb = 26;
const int ledPinbc = 27;
// player C
const int playerC_abcPin = 33;
const int ledPinca = 18;
const int ledPincb = 19;
const int ledPincc = 21;

// game states
String playerA = "";
String playerB = "";
String playerC = "";
int playerA_value;
int playerB_value;
int playerC_value;

String receivedData = "";
bool ableToAns = false;
int playerCount = 0;
int counter = 0;

void setup()
{
    Serial.begin(115200);

    pinMode(ledPinaa, OUTPUT);
    pinMode(ledPinab, OUTPUT);
    pinMode(ledPinac, OUTPUT);
}

void loop()
{
    if (Serial.available())
    {
        receivedData = Serial.readStringUntil('\n'); // Read data until newline
        if (receivedData.startsWith("PC:"))
        {
            if (receivedData.indexOf("choice:True") != -1)
            {
                ableToAns = true;
                playerA = "";
                playerB = "";
                playerC = "";
                counter = 0;
                if (receivedData.indexOf("choice:True1") != -1)
                    playerCount = 1;
                else if (receivedData.indexOf("choice:True2") != -1)
                    playerCount = 2;
                else if (receivedData.indexOf("choice:True3") != -1)
                    playerCount = 3;
            }
            else if (receivedData.indexOf("choice:False") != -1)
                ableToAns = false;
            else
                Serial.println("Invalid choice format!");
        }
    }

    if (ableToAns)
    {
        if (playerCount >= 1 && playerA == "")
        {
            // player A answer
            playerA_value = analogRead(playerA_abcPin);
            updatePlayerState(playerA, playerA_value);
        }
        if (playerCount >= 2 && playerB == "")
        {
            // player B answer
            playerB_value = analogRead(playerB_abcPin);
            updatePlayerState(playerB, playerB_value);
        }
        if (playerCount == 3 && playerC == "")
        {
            // player C answer
            playerC_value = analogRead(playerC_abcPin);
            updatePlayerState(playerC, playerC_value);
        }

        if (playerCount == counter)
        {
            ableToAns = false;
        }
    }

    updateLeds();
}

void updatePlayerState(String &player, int value)
{
    if (player == "" && value < 4000)
    {
        counter++;

        if (value < 1000)
            player = "A";
        else if (value >= 1600 && value < 2000)
            player = "B";
        else if (value >= 3600)
            player = "C";

        // message = "AR:{f:[A],s:[],t:[],c:[0]}";
        Serial.println("AR:{f:[" + playerA + "],s:[" + playerB + "],t:[" + playerC + "],c:[" + counter + "]}");
    }
}

void updateLeds()
{
    if (playerA == "A")
        digitalWrite(ledPinaa, HIGH);
    else if (playerA == "B")
        digitalWrite(ledPinab, HIGH);
    else if (playerA == "C")
        digitalWrite(ledPinac, HIGH);
    else
    {
        digitalWrite(ledPinaa, LOW);
        digitalWrite(ledPinab, LOW);
        digitalWrite(ledPinac, LOW);
    }

    if (playerB == "A")
        digitalWrite(ledPinba, HIGH);
    else if (playerB == "B")
        digitalWrite(ledPinbb, HIGH);
    else if (playerB == "C")
        digitalWrite(ledPinbc, HIGH);
    else
    {
        digitalWrite(ledPinba, LOW);
        digitalWrite(ledPinbb, LOW);
        digitalWrite(ledPinbc, LOW);
    }

    if (playerC == "A")
        digitalWrite(ledPinca, HIGH);
    else if (playerC == "B")
        digitalWrite(ledPincb, HIGH);
    else if (playerC == "C")
        digitalWrite(ledPincc, HIGH);
    else
    {
        digitalWrite(ledPinca, LOW);
        digitalWrite(ledPincb, LOW);
        digitalWrite(ledPincc, LOW);
    }
}