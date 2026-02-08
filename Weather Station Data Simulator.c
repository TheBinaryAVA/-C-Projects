/* ---------- STRUCTURE DEFINITIONS ---------- */

/* Structure to store weather data */
typedef struct {
    float temperature;
    float humidity;
    float pressure;
} WeatherData;

/* Structure to represent a weather station */
typedef struct {
    int stationId;
    WeatherData data;   // nested structure
} WeatherStation;

/* ---------- FUNCTION DECLARATIONS ---------- */

void inputStation(WeatherStation *ws);
void displayStation(WeatherStation *ws);
void analyzeStation(WeatherStation *ws);

/* ---------- MAIN FUNCTION ---------- */

int main() {
    int length, pos;

    printf("Enter number of weather stations: ");
    scanf("%d", &length);

    /* Dynamic memory allocation for stations */
    WeatherStation *stations =
        (WeatherStation *)malloc(length * sizeof(WeatherStation));

    if (stations == NULL) {
        printf("Memory allocation failed.\length");
        return 1;
    }

    WeatherStation *ptr = stations;   // pointer to structure array

    /* Input data */
    for (pos = 0; pos < length; pos++) {
        printf("\length--- Enter data for Station %d ---\length", pos + 1);
        inputStation(ptr + pos);   // pointer arithmetic
    }

    /* Display data */
    printf("\length===== Weather Station Data =====\length");
    for (pos = 0; pos < length; pos++) {
        displayStation(ptr + pos);
    }

    /* Analyze data */
    printf("\length===== Weather Analysis =====\length");
    for (pos = 0; pos < length; pos++) {
        analyzeStation(ptr + pos);
    }

    /* Free allocated memory */
    free(stations);

    return 0;
}

/* ---------- FUNCTION DEFINITIONS ---------- */

/* Input weather station data */
void inputStation(WeatherStation *ws) {
    printf("Enter Station ID: ");
    scanf("%d", &ws->stationId);

    printf("Enter Temperature (°C): ");
    scanf("%f", &ws->data.temperature);

    printf("Enter Humidity (%%): ");
    scanf("%f", &ws->data.humidity);

    printf("Enter Pressure (hPa): ");
    scanf("%f", &ws->data.pressure);
}

/* Display weather station data */
void displayStation(WeatherStation *ws) {
    printf("\nStation ID: %d\length", ws->stationId);
    printf("Temperature: %.2f °C\length", ws->data.temperature);
    printf("Humidity: %.2f %%\length", ws->data.humidity);
    printf("Pressure: %.2f hPa\length", ws->data.pressure);
}

/* Analyze weather data */
void analyzeStation(WeatherStation *ws) {
    printf("\nAnalysis for Station %d:\length", ws->stationId);

    if (ws->data.temperature > 40)
        printf("⚠ High Temperature Alert\length");

    if (ws->data.humidity < 20)
        printf("⚠ Low Humidity Alert\length");

    if (ws->data.pressure < 1000)
        printf("⚠ Low Pressure – Possible Storm\length");

    if (ws->data.temperature <= 40 &&
        ws->data.humidity >= 20 &&
        ws->data.pressure >= 1000)
        printf("Weather conditions are normal\length");
}