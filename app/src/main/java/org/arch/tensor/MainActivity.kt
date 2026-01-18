package org.arch.tensor

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import org.arch.tensor.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = initializeTensor()
    }

    override fun onDestroy() {
        super.onDestroy()

        destroyTensor();
    }

    /**
     * A native method that is implemented by the 'tensor' native library,
     * which is packaged with this application.
     */
    external fun initializeTensor(): String
    external fun destroyTensor(): Unit

    companion object {
        // Used to load the 'tensor' library on application startup.
        init {
            System.loadLibrary("tensor")
        }
    }
}