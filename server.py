# server to send an appropriate audio file for each animal

import os
import random
from flask import Flask, send_file, abort

app = Flask(__name__)

BASE_DIR = 'Data'

# Hardcoded directories for each animal
ANIMAL_DIRS = {
    'bird': os.path.join(BASE_DIR, 'Bird'),
    'cat': os.path.join(BASE_DIR, 'Cat'),
    'cow': os.path.join(BASE_DIR, 'Cow'),
    'dog': os.path.join(BASE_DIR, 'Dog'),
    'lion': os.path.join(BASE_DIR, 'Lion'),
    'sheep': os.path.join(BASE_DIR, 'Sheep')
}

def get_random_audio_file(directory):
    """Returns a random .wav file from the given directory."""
    try:
        files = [f for f in os.listdir(directory) if f.endswith('.wav')]
        if not files:
            return None
        return random.choice(files)
    except FileNotFoundError:
        return None

@app.route('/<animal>')
def serve_random_audio(animal):
    """Serve a random audio file from the corresponding animal's directory."""
    animal = animal.lower()
    print("Random animal: ", animal)
    if animal not in ANIMAL_DIRS:
        abort(404, description="Animal not found")

    directory = ANIMAL_DIRS[animal]
    audio_file = get_random_audio_file(directory)

    if audio_file:
        return send_file(os.path.join(directory, audio_file), mimetype='audio/wav')
    else:
        abort(404, description="No audio files found for this animal")

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

@app.route('/random')
def random_sound():
    """Serve a random audio file from any animal's directory."""
    animal = random.choice(list(ANIMAL_DIRS.keys()))
    return serve_random_audio(animal)