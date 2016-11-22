// Shading a gradient
void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    vec2 coord = fragCoord.xy / iResolution.xy;

    // White to color
	//fragColor = vec4(1.0, 1.0 - coord.x, 1.0 - coord.x, 1.0);

    // Color to white
   	fragColor = vec4(1.0, coord.x, coord.x, 1.0);
}
