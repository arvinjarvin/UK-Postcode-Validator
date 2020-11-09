#include <iostream>
#include <algorithm>

using namespace std;

enum POSTCODE_STATUS
{
    OK,
    INVALID_LENGTH,
    INVALID_CHARACTER,
    INVALID_FORMAT
};

string POSTCODE_FORMATS[6] = {
        "ANNAA",
        "ANNNAA",
        "AANNAA",
        "AANNNAA",
        "ANANAA",
        "AANANAA"
};

POSTCODE_STATUS validatePostcode(string postcode);
bool isValidCharacter(char character);
bool isAlpha(char character);
void emitFriendlyError(string postcode, int index);
void emitError(string error);

int main()
{
    string inputPostcode;

    cout << "Welcome to the postcode validator, enter a postcode and I will validate it." << endl;
    cout << "Enter the first postcode: ";
    while(getline(cin, inputPostcode))
    {
        inputPostcode.erase(remove(inputPostcode.begin(), inputPostcode.end(), ' '), inputPostcode.end());

        POSTCODE_STATUS inputResult = validatePostcode(inputPostcode);

        if(inputResult != OK)
        {
            cout << "Error: ";

            switch(inputResult)
            {
                case INVALID_CHARACTER:
                    cout << "There was an invalid character in your postcode." << endl;
                    break;
                case INVALID_LENGTH:
                    cout << "Your postcode's length does not meet the requirements." << endl;
                    break;
                case INVALID_FORMAT:
                    cout << "The format of this postcode is invalid." << endl;
                    break;
                default:
                    cout << "Uncaught exception." << endl;
            }

            cout << "Enter another postcode: ";
            continue;
        }

        cout << "That postcode, " << inputPostcode << ", is valid!" << endl;

        cout << "Enter another postcode: ";
    }
}

POSTCODE_STATUS validatePostcode(string postcode)
{
    POSTCODE_STATUS currentPostcodeStatus = OK;

    string compiled_postcode;

    if(postcode.length() < 5)
    {
        currentPostcodeStatus = INVALID_LENGTH;
        return currentPostcodeStatus;
    }

    for(int i = 0; i <= postcode.length() - 1; i++)
    {
        if(!isValidCharacter(postcode[i])) {
            emitFriendlyError(postcode, i);
            currentPostcodeStatus = INVALID_CHARACTER;
            break;
        }

        if(isalpha(postcode[i]))
        {
            compiled_postcode = compiled_postcode + "A";
        } else  compiled_postcode = compiled_postcode + "N";
    }

    if(postcode[0] == 'Q' ||
    postcode[0] == 'V' ||
    postcode[0] == 'X' )
    {
        emitFriendlyError(postcode, 0);
        currentPostcodeStatus = INVALID_CHARACTER;
        return currentPostcodeStatus;
    }

    if(postcode[1] == 'I' ||
       postcode[1] == 'J' ||
       postcode[1] == 'Z')
    {
        emitFriendlyError(postcode, 1);
        currentPostcodeStatus = INVALID_CHARACTER;
        return currentPostcodeStatus;
    }

    if(isalpha(postcode[2]))
    {
        if(postcode[2] == 'I' ||
                postcode[2] == 'L' ||
                postcode[2] == 'M' ||
                postcode[2] == 'N' ||
                postcode[2] == 'O' ||
                postcode[2] == 'P' ||
                postcode[2] == 'Q' ||
                postcode[2] == 'R' ||
                postcode[2] == 'V' ||
                postcode[2] == 'X' ||
                postcode[2] == 'Y' ||
                postcode[2] == 'Z')
        {
            emitFriendlyError(postcode, 2);
            currentPostcodeStatus = INVALID_CHARACTER;
            return currentPostcodeStatus;
        }
    }

    if(compiled_postcode.substr(compiled_postcode.length()-3, 3) != "NAA")
    {
        emitError("Second half of postcode should match the format, 'NAA'.");
        currentPostcodeStatus = INVALID_FORMAT;
        return currentPostcodeStatus;
    }

    for(int i = compiled_postcode.length()-4; i <= compiled_postcode.length(); i++)
    {
        if(postcode[i] == 'C' ||
                postcode[i] == 'I' ||
                postcode[i] == 'K' ||
                postcode[i] == 'M' ||
                postcode[i] == 'O' ||
                postcode[i] == 'V')
        {
            emitError("Second half of postcode cannot contain C, I, K, M, O or V.");
            currentPostcodeStatus = INVALID_CHARACTER;
            return currentPostcodeStatus;
        }
    }

    bool isMatchedFormat = false;

    for(string format : POSTCODE_FORMATS)
    {
        if(compiled_postcode == format)
        {
            isMatchedFormat = true;
        }
    }

    if(!isMatchedFormat) currentPostcodeStatus = INVALID_FORMAT;

    return currentPostcodeStatus;
}

bool isValidCharacter(char character)
{
    bool isValid = true;

    if(!isalnum(character))
    {
        cout << character;
        isValid = false;
    }

    return isValid;
}

bool isAlpha(char character)
{
    bool currentIsAlpha = true;

    if(!isalpha(character))
    {
        currentIsAlpha = false;
    }

    return currentIsAlpha;
}

void emitFriendlyError(string postcode, int index)
{
    string genericErrorMessage = "Encountered an error: ";
    cout << genericErrorMessage << postcode << endl;
    string errorOutput;
    for(int i = 1; i<=genericErrorMessage.length(); i++)
        errorOutput+=" ";
    for(int i = 0; i<=index; i++)
        errorOutput+=" ";

    errorOutput+="^";

    cout << errorOutput << endl;
}

void emitError(string error)
{
    cout << "Error: " << error << endl;
}