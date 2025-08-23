from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
import os
from openai import OpenAI
from dotenv import load_dotenv

load_dotenv()

app = FastAPI(title="Music Copilot API", version="1.0.0")

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

client = OpenAI(api_key=os.getenv("OPENAI_API_KEY"))

class MusicQuery(BaseModel):
    prompt: str
    context: str = ""

class MusicResponse(BaseModel):
    response: str
    suggestions: list[str] = []

@app.get("/")
async def root():
    return {"message": "Music Copilot API"}

@app.post("/chat", response_model=MusicResponse)
async def chat_with_copilot(query: MusicQuery):
    try:
        system_prompt = """You are a music copilot assistant. Help users with music-related questions, recommendations, and creative tasks. 
        You can assist with songwriting, music theory, artist recommendations, playlist creation, and music production advice."""
        
        messages = [
            {"role": "system", "content": system_prompt},
        ]
        
        if query.context:
            messages.append({"role": "user", "content": f"Context: {query.context}"})
        
        messages.append({"role": "user", "content": query.prompt})
        
        response = client.chat.completions.create(
            model="gpt-4",
            messages=messages,
            max_tokens=500,
            temperature=0.7
        )
        
        return MusicResponse(
            response=response.choices[0].message.content,
            suggestions=[]
        )
        
    except Exception as e:
        raise HTTPException(status_code=500, detail=f"Error processing request: {str(e)}")

@app.get("/health")
async def health_check():
    return {"status": "healthy"}

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)