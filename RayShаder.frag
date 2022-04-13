#version 130
uniform vec3 u_pos;
uniform vec2 u_resolution;
uniform sampler2D u_sample;
//функция пересечаения луча и сферы
//ro - точка выхода луча
//кв - напрввления луча 
//ra - радиус сфера
vec2 sphIntersect(in vec3 ro, in vec3 rd, float ra) {
	float b = dot(ro, rd);
	float c = dot(ro, ro) - ra * ra;
	float h = b * b - c;
	if(h < 0.0) return vec2(-1.0);
	h = sqrt(h);
	return vec2(-b - h, -b + h);
}
float plaIntersect(in vec3 ro, in vec3 rd, in vec4 p) {
	return -(dot(ro, p.xyz) + p.w) / dot(rd, p.xyz);
}
//функция выпуска луча
vec3 castRay(inout vec3 ro, inout vec3 rd) {
	//проверка пересенчения луча и сферы
	//it хранит растояние до пересечения (их может быть два)
	vec2 it = sphIntersect(ro,rd,0.5);

	if(it.x < 0.0)
		return vec3(0.0);	
	else{
	vec3 itPos = ro + rd*it.x;
	//нормаль работает так только для сферы
	vec3 n = itPos;
	vec3 light = normalize(vec3(-0.5,0.75,1.0));
	float diffise = dot(light,n);
	return vec3(diffise);
	}
}

void main() {
	vec2 uv = (gl_TexCoord[0].xy - 0.5)* u_resolution / u_resolution.y;
	vec3 rayOrigin = vec3(-5.0, 1.0, 0.0);
	vec3 rayDirection = normalize(vec3(1.0,uv));
	vec3 col = castRay(rayOrigin,rayDirection);

	gl_FragColor = vec4(col, 1.0);

}