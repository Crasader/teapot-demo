// Checkerboard converting coordinates to 0-1.0 scale
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 coord = fragCoord.xy / iResolution.xy;
    vec4 black = vec4(0,0,0,0);
    vec4 white = vec4(1,1,1,1);
    vec4 red = vec4(1,0,0,1);
    vec4 green = vec4(0,1,0,1);
    vec4 blue = vec4(0,0,1,1);
    vec4 yellow = vec4(1,1,0,1);
    vec4 magenta = vec4(1,0,1,1);
    vec4 cyan = vec4(0,1,1,1);

    // Bottom-Left
    if(coord.x < 0.5 && coord.y < 0.5) {
        fragColor = red;
    }

    // Top-Left
    if(coord.x < 0.5 && coord.y > 0.5) {
        fragColor = green;
    }

    // Bottom-Right
    if(coord.x > 0.5 && coord.y < 0.5) {
        fragColor = blue;
    }

    // Top-Right
    if(coord.x > 0.5 && coord.y > 0.5) {
        fragColor = yellow;
    }
}

/* Checkerboard NOT converting coordinates to 0-1.0 scale
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 coord = fragCoord;
    vec4 black = vec4(0,0,0,0);
    vec4 white = vec4(1,1,1,1);

    if(coord.x < iResolution.x / 2.0 &&
       coord.y < iResolution.y / 2.0) {
        fragColor = black;
    }

    if(coord.x < iResolution.x / 2.0 &&
       coord.y > iResolution.y / 2.0) {
        fragColor = white;
    }

    if(coord.x > iResolution.x / 2.0 &&
       coord.y < iResolution.y / 2.0) {
        fragColor = white;
    }

    if(coord.x > iResolution.x / 2.0 &&
       coord.y > iResolution.y / 2.0) {
        fragColor = black;
    }
}
*/
/* SPLIT SCREEN B&W
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 coord = fragCoord;
    vec4 black = vec4(0,0,0,0);
    vec4 white = vec4(1,1,1,1);

    if(coord.x < iResolution.x / 2.0) {
        fragColor = black;
    }

    if(coord.x > iResolution.x / 2.0) {
        fragColor = white;
    }
}
*/
