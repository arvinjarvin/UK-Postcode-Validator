# Postcode Validator
This is a postcode validator for the United Kingdom in progress.

It works simply via a while loop and some validation.

## Validation Criteria

**Available Postcode Formats:**

AN NAA\
ANN NAA\
AAN NAA\
AANN NAA\
ANA NAA\
AANA NAA

Where A is an alpha character, and N is a numeric character.

- The letters Q, V, and V can't be used in the first position
- The letters I, J and Z can't be used in the second position
- The only letters which can be present in the third position are A, B, C, D, E, F, G, H, J, K, S, T, U, and W.
- The second half of the postcode will consistently follow the format, 'NAA'
- The letters C, I, K, M, O, and V are not used in the second half.

