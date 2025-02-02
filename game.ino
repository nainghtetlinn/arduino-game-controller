// player A
const int ledPinaa = 2;
const int ledPinab = 13;
const int ledPinac = 14;
const int playerA_abcPin = 34;
// player B
const int ledPinba = 2;
const int ledPinbb = 13;
const int ledPinbc = 14;
const int playerB_abcPin = 34;
// player C
const int ledPinca = 2;
const int ledPincb = 13;
const int ledPincc = 14;
const int playerC_abcPin = 34;

// game states
String playerA = "0";
String playerB = "0";
String playerC = "0";

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
    updateLeds();

    if (Serial.available())
    {
        receivedData = Serial.readStringUntil('\n'); // Read data until newline
        if (receivedData.startsWith("PC:"))
        {
            if (receivedData.indexOf("choice:True") != -1)
            {
                ableToAns = true;
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
        int playerA_value = analogRead(playerA_abcPin);
        int playerB_value = analogRead(playerB_abcPin);
        int playerC_value = analogRead(playerC_abcPin);

        // message = "AR:{f:[A],s:[0],t:[0],c:[0]}";
        // player A answer
        updatePlayerState(playerA, playerA_value);

        // player B answer
        updatePlayerState(playerB, playerB_value);

        // player C answer
        updatePlayerState(playerC, playerC_value);

        String message = "AR:{f:[" + playerA + "],s:[" + playerB + "],t:[" + playerC + "],c:[" + counter + "]}";

        Serial.println(message);

        if (playerCount == counter)
        {
            ableToAns = false;
        }
    }
}

void updatePlayerState(String &player, int value)
{
    if (player == "0" && value < 4000)
    {
        counter++;

        if (value < 1000)
            player = "A";
        else if (value >= 1600 && value < 2000)
            player = "B";
        else if (value >= 3600)
            player = "C";
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