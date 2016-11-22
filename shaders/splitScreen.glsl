void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 coord = fragCoord.xy;
    vec4 black = vec4(0,0,0,0);
    vec4 white = vec4(1,1,1,1);
    
    if(coord.x < iResolution.x / 2.0) {
        fragColor = black;
    }
    
    if(coord.x > iResolution.x / 2.0) {
        fragColor = white;
    }
}